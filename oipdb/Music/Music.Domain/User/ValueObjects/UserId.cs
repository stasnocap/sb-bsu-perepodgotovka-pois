using Music.Domain.Common.Models;

namespace Music.Domain.User.ValueObjects;

public class UserId : ValueObject
{
    public Guid Id { get; }

    private UserId(Guid id)
    {
        Id = id;
    }
    
    public static UserId CreateUnique()
    {
        return new(Guid.NewGuid());
    }
    
    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Id;
    }
}