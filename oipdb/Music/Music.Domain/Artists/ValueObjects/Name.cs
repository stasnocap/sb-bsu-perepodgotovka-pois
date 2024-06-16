using ErrorOr;
using Music.Domain.Common.Models;

namespace Music.Domain.Artists.ValueObjects;

public class Name : ValueObject
{
    public string Value { get; }

    private Name(string value)
    {
        Value = value;
    }

    public static ErrorOr<Name> Create(string value)
    {
        return new Name(value);
    }
    
    protected override IEnumerable<object> GetEqualityComponents()
    {
        yield return Value;
    }
}