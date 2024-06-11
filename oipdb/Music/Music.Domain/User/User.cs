using Music.Domain.Common.Models;
using Music.Domain.User.Events;
using Music.Domain.User.ValueObjects;

namespace Music.Domain.User;

public sealed class User : AggregateRoot<UserId>
{
    public FirstName FirstName { get; }
    public LastName LastName { get; }
    public Email Email { get; }
    public PasswordHash PasswordHash { get; set; }

    private User(UserId id, FirstName firstName, LastName lastName, Email email) : base(id)
    {
        FirstName = firstName;
        LastName = lastName;
        Email = email;
    }

    public static User Create(FirstName firstName, LastName lastName, Email email)
    {
        var user = new User(UserId.CreateUnique(), firstName, lastName, email);
        
        user.AddDomainEvent(new UserCreatedDomainEvent(user));

        return user;
    }
}