using Music.Domain.Common.Models;
using Music.Domain.User.Events;
using Music.Domain.User.ValueObjects;

namespace Music.Domain.User;

public sealed class User : AggregateRoot<UserId>
{
    public string FirstName { get; }
    public string LastName { get; }
    public string Email { get; }
    public string Password { get; }

    private User(UserId id, string firstName, string lastName, string email, string password) : base(id)
    {
        FirstName = firstName;
        LastName = lastName;
        Email = email;
        Password = password;
    }

    public static User Create(string firstName, string lastName, string email, string password)
    {
        var user = new User(UserId.CreateUnique(), firstName, lastName, email, password);
        
        user.AddDomainEvent(new UserCreatedDomainEvent(user));

        return user;
    }
}