using ErrorOr;
using Music.Domain.Common.Models;

namespace Music.Domain.User.ValueObjects;

public class PasswordHash : ValueObject
{
    public string Value { get; }

    private PasswordHash(string value)
    {
        Value = value;
    }

    public static ErrorOr<PasswordHash> Create(string value)
    {
        return new PasswordHash(value);
    }
    
    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}