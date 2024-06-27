using Music.Domain.Common.Models;

namespace Music.Domain.Tracks.ValueObjects;

public class TrackId : ValueObject
{
    public Guid Value { get; }

    private TrackId(Guid value)
    {
        Value = value;
    }
    
    public static TrackId Create(Guid id)
    {
        return new(id);
    }
    
    public static TrackId CreateUnique()
    {
        return new(Guid.NewGuid());
    }
    
    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}