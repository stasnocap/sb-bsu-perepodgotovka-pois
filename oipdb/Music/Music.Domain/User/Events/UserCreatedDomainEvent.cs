using Music.Domain.Common.Models;

namespace Music.Domain.User.Events;

public record UserCreatedDomainEvent(User User) : IDomainEvent;