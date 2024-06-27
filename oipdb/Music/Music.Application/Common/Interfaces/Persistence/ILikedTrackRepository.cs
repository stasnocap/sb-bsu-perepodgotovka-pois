using Music.Domain.LikedTracks;
using Music.Domain.Tracks.ValueObjects;
using Music.Domain.Users.ValueObjects;

namespace Music.Application.Common.Interfaces.Persistence;

public interface ILikedTrackRepository
{
    Task AddAsync(LikedTrack likedTrack, CancellationToken cancellationToken);
    Task<bool> AnyAsync(TrackId trackId, UserId userId, CancellationToken cancellationToken);
}