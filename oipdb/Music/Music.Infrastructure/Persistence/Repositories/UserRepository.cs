using Dapper;
using Microsoft.Extensions.Configuration;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.User;
using Music.Infrastructure.Persistence.Interceptors;

namespace Music.Infrastructure.Persistence.Repositories;

public class UserRepository(IConfiguration configuration, PublishDomainEventsInterceptor publishDomainEventsInterceptor)
    : BaseRepository(configuration, publishDomainEventsInterceptor), IUserRepository
{
    public async Task<User?> GetUserByEmailAsync(string email, CancellationToken cancellationToken)
    {
        const string sql = @"SELECT * FROM ""Users"" WHERE ""Email"" = '@Email'";
        
        var user = await Connection.QuerySingleOrDefaultAsync<User>(sql, email);
        
        return user;
    }

    public async Task AddAsync(User user, CancellationToken cancellationToken)
    {
        await BeginTransactionAsync(cancellationToken);
        
        const string sql = @"INSERT INTO ""Users""(""Id"", ""FirstName"", ""LastName"", ""Email"", ""Password"") VALUES (@Id, @FirstName, @LastName, @Email, @Password)";

        await Connection.ExecuteAsync(sql, new
        {
            user.Id.Id, user.FirstName,
        });

        await CommitAsync([user], cancellationToken);
    }
}