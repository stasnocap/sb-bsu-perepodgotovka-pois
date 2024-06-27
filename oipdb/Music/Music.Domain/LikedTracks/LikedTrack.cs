using Music.Domain.Common.Models;
using Music.Domain.LikedTracks.ValueObjects;
using Music.Domain.Tracks.ValueObjects;
using Music.Domain.Users.ValueObjects;

namespace Music.Domain.LikedTracks;

public class LikedTrack : AggregateRoot<LikedTrackId>
{
    public TrackId TrackId { get; }
    public UserId UserId { get; }

    private LikedTrack(LikedTrackId id, TrackId trackId, UserId userId) : base(id)
    {
        TrackId = trackId;
        UserId = userId;
    }

    public static ErrorOr.ErrorOr<LikedTrack> Create(TrackId trackId, UserId userId)
    {
        return new LikedTrack(LikedTrackId.CreateUnique(), trackId, userId);
    }
}