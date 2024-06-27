using Music.Domain.Common.Models;

namespace Music.Domain.Tracks.Events;

public record TrackCreatedDomainEvent(Track Track) : IDomainEvent;