using ErrorOr;
using Music.Domain.Common.Models;

namespace Music.Domain.Users.ValueObjects;

public class Password : ValueObject
{
    public string Value { get; }

    private Password(string value)
    {
        Value = value;
    }

    public static ErrorOr<Password> Create(string value)
    {
        return new Password(value);
    }
    
    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}