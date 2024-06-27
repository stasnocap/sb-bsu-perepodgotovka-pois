using Mapster;
using Music.Application.Followers.Commands.CreateFollower;
using Music.Contracts.Followers;
using Music.Domain.Artists.ValueObjects;

namespace Music.Api.Common.Mapping;

public class FollowerMappingConfiguration : IRegister
{
    public void Register(TypeAdapterConfig config)
    {
        config.NewConfig<CreateFollowerRequest, CreateFollowerCommand>()
            .Map(dest => dest.ArtistId, src => ArtistId.Create(src.ArtistId));
    }
}