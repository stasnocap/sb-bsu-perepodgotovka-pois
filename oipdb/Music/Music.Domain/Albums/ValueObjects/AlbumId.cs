using Music.Domain.Common.Models;

namespace Music.Domain.Albums.ValueObjects;

public class AlbumId : ValueObject
{
    public Guid Value { get; }

    private AlbumId(Guid value)
    {
        Value = value;
    }

    public static AlbumId Create(Guid id)
    {
        return new(id);
    }

    public static AlbumId CreateUnique()
    {
        return new(Guid.NewGuid());
    }

    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}