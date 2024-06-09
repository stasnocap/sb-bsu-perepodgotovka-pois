using Music.Domain.Common.Models;

namespace Music.Domain.Artist.Events;

public record ArtistCreatedDomainEvent(Artist Artist) : IDomainEvent;