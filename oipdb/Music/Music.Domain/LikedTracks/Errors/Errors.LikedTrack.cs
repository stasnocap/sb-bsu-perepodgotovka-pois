using ErrorOr;

namespace Music.Domain.LikedTracks.Errors;

public static partial class Errors
{
    public static class LikedTrack
    {
        public static Error AlreadyExists => Error.Conflict(code: "LikedTrack.AlreadyExists", description: "You already liked this track.");
    }
}