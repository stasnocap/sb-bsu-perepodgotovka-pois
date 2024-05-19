using Music.Domain.Common.Models;

namespace Music.Domain.Artist.ValueObjects;

public sealed class ArtistId : ValueObject
{
    public Guid Id { get; }

    private ArtistId(Guid id)
    {
        Id = id;
    }

    public static ArtistId CreateUnique()
    {
        return new(Guid.NewGuid());
    }

    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Id;
    }
}