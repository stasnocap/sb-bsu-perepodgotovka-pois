using Music.Domain.Artists.ValueObjects;
using Music.Domain.Followers;
using Music.Domain.Users.ValueObjects;

namespace Music.Application.Common.Interfaces.Persistence;

public interface IFollowerRepository
{
    Task AddAsync(Follower follower, CancellationToken cancellationToken);
    Task<bool> IsAlreadyFollowed(ArtistId artistId, UserId userId);
}