using Music.Domain.Common.Models;

namespace Music.Domain.Artists.ValueObjects;

public sealed class ArtistId : ValueObject
{
    public Guid Value { get; }

    private ArtistId(Guid value)
    {
        Value = value;
    }
    
    public static ArtistId Create(Guid id)
    {
        return new(id);
    }

    public static ArtistId CreateUnique()
    {
        return new(Guid.NewGuid());
    }

    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}