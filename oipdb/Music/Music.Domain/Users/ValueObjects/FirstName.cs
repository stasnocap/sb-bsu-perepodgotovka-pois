using ErrorOr;
using Music.Domain.Common.Models;

namespace Music.Domain.Users.ValueObjects;

public class FirstName : ValueObject
{
    public string Value { get; }

    private FirstName(string value)
    {
        Value = value;
    }

    public static ErrorOr<FirstName> Create(string value)
    {
        return new FirstName(value);
    }
    
    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}