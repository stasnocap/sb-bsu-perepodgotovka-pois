using Music.Domain.Common.Models;
using Music.Domain.User.Events;
using Music.Domain.User.ValueObjects;

namespace Music.Domain.User;

public sealed class User : AggregateRoot<UserId>
{
    public FirstName FirstName { get; }
    public LastName LastName { get; }
    public Email Email { get; }
    public Password Password { get; }

    private User(UserId id, FirstName firstName, LastName lastName, Email email, Password password) : base(id)
    {
        FirstName = firstName;
        LastName = lastName;
        Email = email;
        Password = password;
    }

    public static User Create(FirstName firstName, LastName lastName, Email email, Password password)
    {
        var user = new User(UserId.CreateUnique(), firstName, lastName, email, password);
        
        user.AddDomainEvent(new UserCreatedDomainEvent(user));

        return user;
    }
}