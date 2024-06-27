using ErrorOr;

namespace Music.Domain.Followers.Errors;

public static class Errors
{
    public static class Follower
    {
        public static readonly Error AlreadyFollowed = Error.Conflict("Follower.AlreadyFollowed", "You are already following this artist.");
    }
}