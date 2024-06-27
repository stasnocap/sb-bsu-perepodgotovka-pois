using Mapster;
using Music.Application.LikedTracks.Commands;
using Music.Contracts.LikedTracks;
using Music.Domain.Tracks.ValueObjects;

namespace Music.Api.Common.Mapping;

public class LikedTrackMappingConfiguration : IRegister
{
    public void Register(TypeAdapterConfig config)
    {
        config.NewConfig<LikeTrackRequest, LikeTrackCommand>()
            .Map(dest => dest.TrackId, src => TrackId.Create(src.TrackId));
    }
}