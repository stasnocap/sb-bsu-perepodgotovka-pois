using Music.Domain.Artists.ValueObjects;
using Music.Domain.Common.Models;
using Music.Domain.Followers.ValueObjects;
using Music.Domain.Users.ValueObjects;

namespace Music.Domain.Followers;

public class Follower : AggregateRoot<FollowerId>
{
    public ArtistId ArtistId { get; }
    public UserId UserId { get; }

    private Follower(FollowerId id, ArtistId artistId, UserId userId) : base(id)
    {
        ArtistId = artistId;
        UserId = userId;
    }

    public static ErrorOr.ErrorOr<Follower> Create(ArtistId artistId, UserId userId)
    {
        return new Follower(FollowerId.CreateUnique(), artistId, userId);
    }
}