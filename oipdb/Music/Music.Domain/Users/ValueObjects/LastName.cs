using ErrorOr;
using Music.Domain.Common.Models;

namespace Music.Domain.Users.ValueObjects;

public class LastName : ValueObject
{
    public string Value { get; }

    private LastName(string value)
    {
        Value = value;
    }

    public static ErrorOr<LastName> Create(string value)
    {
        return new LastName(value);
    }
    
    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}