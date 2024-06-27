using Music.Domain.Common.Models;

namespace Music.Domain.Followers.Events;

public record FollowerCreatedDomainEvent(Follower Follower) : IDomainEvent;