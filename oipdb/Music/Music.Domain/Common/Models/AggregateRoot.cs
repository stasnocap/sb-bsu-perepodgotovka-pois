namespace Music.Domain.Common.Models;

public class AggregateRoot<TId> : Entity<TId>
    where TId : notnull
{
    protected AggregateRoot(TId artistId) : base(artistId)
    {
    }
}