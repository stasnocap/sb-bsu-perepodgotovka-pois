using ErrorOr;
using MediatR;
using Music.Application.Common.Interfaces.Persistence;
using Music.Application.Common.Interfaces.Services;
using Music.Domain.Artists.Errors;
using Music.Domain.Followers;
using Music.Domain.Followers.ValueObjects;

namespace Music.Application.Followers.Commands.CreateFollower;

public class CreateFollowerCommandHandler(IFollowerRepository _followerRepository, IArtistRepository _artistRepository, IUserContext _userContext) : IRequestHandler<CreateFollowerCommand, ErrorOr<FollowerId>>
{
    public async Task<ErrorOr<FollowerId>> Handle(CreateFollowerCommand request, CancellationToken cancellationToken)
    {
        var artist = await _artistRepository.SingleOrDefaultAsync(request.ArtistId, cancellationToken);
        if (artist is null)
        {
            return Errors.Artist.NotFound;
        }
        
        var userId = _userContext.GetCurrentUserId();

        if (await _followerRepository.IsAlreadyFollowed(artist.Id, userId))
        {
            return Domain.Followers.Errors.Errors.Follower.AlreadyFollowed;
        }
            
        var errorOrFollower = Follower.Create(artist.Id, userId);

        if (errorOrFollower.IsError)
        {
            return errorOrFollower.Errors;
        }

        var follower = errorOrFollower.Value;

        await _followerRepository.AddAsync(follower, cancellationToken);

        return follower.Id;
    }
}