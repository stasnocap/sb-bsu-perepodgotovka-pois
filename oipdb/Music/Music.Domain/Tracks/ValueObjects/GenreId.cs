using Music.Domain.Common.Models;

namespace Music.Domain.Tracks.ValueObjects;

public class GenreId : ValueObject
{
    public Guid Value { get; }

    private GenreId(Guid value)
    {
        Value = value;
    }
    
    public static GenreId Create(Guid id)
    {
        return new(id);
    }
    
    public static GenreId CreateUnique()
    {
        return new(Guid.NewGuid());
    }
    
    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}