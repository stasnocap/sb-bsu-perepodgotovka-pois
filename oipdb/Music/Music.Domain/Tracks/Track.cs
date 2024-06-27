using Music.Domain.Albums.ValueObjects;
using Music.Domain.Artists.ValueObjects;
using Music.Domain.Common.Models;
using Music.Domain.Tracks.Entities;
using Music.Domain.Tracks.Events;
using Music.Domain.Tracks.ValueObjects;

namespace Music.Domain.Tracks;

public class Track : AggregateRoot<TrackId>
{
    public AlbumId AlbumId { get; }
    public ArtistId ArtistId { get; }
    public Genre Genre { get; }

    private Track(TrackId id, AlbumId albumId, ArtistId artistId, Genre genre) : base(id)
    {
        AlbumId = albumId;
        ArtistId = artistId;
        Genre = genre;
    }

    public static Track Create(AlbumId albumId, ArtistId artistId, Genre genre)
    {
        var track = new Track(TrackId.CreateUnique(), albumId, artistId, genre);
        
        track.AddDomainEvent(new TrackCreatedDomainEvent(track));
        
        return track;
    }
}