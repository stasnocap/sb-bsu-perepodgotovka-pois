using Mapster;
using Music.Application.Artists.Commands.ChangeArtistName;
using Music.Application.Artists.Queries.FansAlsoLikeArtists;
using Music.Contracts.Artists;
using Music.Contracts.Artists.Requests;
using Music.Domain.Artists.ValueObjects;
using Music.Domain.Users.ValueObjects;

namespace Music.Api.Common.Mapping;

public class ArtistMappingConfiguration : IRegister
{
    public void Register(TypeAdapterConfig config)
    {
        config.NewConfig<ChangeArtistNameRequest, ChangeArtistNameCommand>()
            .Map(dest => dest.Id, src => ArtistId.Create(src.Id));
        
        config.NewConfig<FansAlsoLikeArtistsRequest, FansAlsoLikeArtistsQuery>()
            .Map(dest => dest.ArtistId, src => ArtistId.Create(src.ArtistId))
            ;
    }
}