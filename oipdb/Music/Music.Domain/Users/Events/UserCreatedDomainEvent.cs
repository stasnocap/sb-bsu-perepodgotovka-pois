using Music.Domain.Common.Models;

namespace Music.Domain.Users.Events;

public record UserCreatedDomainEvent(User User) : IDomainEvent;