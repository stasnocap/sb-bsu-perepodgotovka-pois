using ErrorOr;
using Music.Domain.Common.Models;

namespace Music.Domain.Users.ValueObjects;

public class UserId : ValueObject
{
    public Guid Value { get; }

    private UserId(Guid value)
    {
        Value = value;
    }
    
    public static UserId Create(Guid id)
    {
        return new(id);
    }
    
    public static UserId CreateUnique()
    {
        return new(Guid.NewGuid());
    }
    
    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}