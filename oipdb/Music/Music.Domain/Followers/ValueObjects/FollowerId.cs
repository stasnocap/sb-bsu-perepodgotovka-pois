using Music.Domain.Common.Models;

namespace Music.Domain.Followers.ValueObjects;

public sealed class FollowerId : ValueObject
{
    public Guid Value { get; }

    private FollowerId(Guid value)
    {
        Value = value;
    }
    
    public static FollowerId Create(Guid id)
    {
        return new(id);
    }

    public static FollowerId CreateUnique()
    {
        return new(Guid.NewGuid());
    }

    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}