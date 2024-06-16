using Music.Domain.Common.Models;

namespace Music.Domain.Artists.Events;

public record ArtistCreatedDomainEvent(Artist Artist) : IDomainEvent;