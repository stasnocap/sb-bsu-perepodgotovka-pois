using Music.Domain.Common.Models;

namespace Music.Domain.LikedTracks.ValueObjects;

public class LikedTrackId : ValueObject
{
    public Guid Value { get; }

    private LikedTrackId(Guid value)
    {
        Value = value;
    }
    
    public static LikedTrackId Create(Guid id)
    {
        return new(id);
    }

    public static LikedTrackId CreateUnique()
    {
        return new(Guid.NewGuid());
    }

    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}