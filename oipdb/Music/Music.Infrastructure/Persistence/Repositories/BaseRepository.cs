using Microsoft.Extensions.Configuration;
using Music.Domain.Common.Models;
using Music.Infrastructure.Persistence.Interceptors;
using Npgsql;

namespace Music.Infrastructure.Persistence.Repositories;

public abstract class BaseRepository(
    IConfiguration configuration,
    PublishDomainEventsInterceptor publishDomainEventsInterceptor)
    : IDisposable, IAsyncDisposable
{
    private readonly PublishDomainEventsInterceptor _publishDomainEventsInterceptor = publishDomainEventsInterceptor;
    
    protected readonly NpgsqlConnection Connection = new(configuration.GetConnectionString("Database"));

    private NpgsqlTransaction? _transaction;

    protected async Task BeginTransactionAsync(CancellationToken cancellationToken)
    {
        await Connection.OpenAsync(cancellationToken);
        _transaction = await Connection.BeginTransactionAsync(cancellationToken);
    }

    protected async Task CommitAsync(IEnumerable<IHasDomainEvents> entities, CancellationToken cancellationToken)
    {
        if (_transaction is null)
        {
            return;
        }

        await _publishDomainEventsInterceptor.PublishDomainEvents(entities, cancellationToken);

        await _transaction.CommitAsync(cancellationToken);
    }

    public void Dispose()
    {
        Connection.Dispose();
    }

    public async ValueTask DisposeAsync()
    {
        await Connection.DisposeAsync();
    }
}