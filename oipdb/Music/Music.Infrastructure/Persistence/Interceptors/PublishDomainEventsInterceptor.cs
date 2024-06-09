using MediatR;
using Music.Domain.Common.Models;

namespace Music.Infrastructure.Persistence.Interceptors;

public class PublishDomainEventsInterceptor(IPublisher _publisher)
{
    public async Task PublishDomainEvents(IEnumerable<IHasDomainEvents> entities, CancellationToken cancellationToken)
    {
        foreach (var domainEvent in entities.SelectMany(e =>
                 {
                     var domainEvents = e.DomainEvents;
                     e.ClearDomainEvents();
                     return domainEvents;
                 }))
        {
            
            await _publisher.Publish(domainEvent, cancellationToken);
        }
    }
}