using ErrorOr;
using MediatR;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.Artists;
using Music.Domain.Artists.Errors;
using Music.Domain.Artists.ValueObjects;

namespace Music.Application.Artists.Commands.CreateArtist;

public class CreateArtistCommandHandler(IArtistRepository _artistRepository) : IRequestHandler<CreateArtistCommand, ErrorOr<ArtistId>>
{
    public async Task<ErrorOr<ArtistId>> Handle(CreateArtistCommand request, CancellationToken cancellationToken)
    {
        var errors = new List<Error>();

        var errorOrName = Name.Create(request.Name);
        errors.AddRange(errorOrName.ErrorsOrEmptyList);
        var name = errorOrName.Value;

        if (!errorOrName.IsError && await _artistRepository.AnyAsync(name, cancellationToken))
        {
            errors.Add(Errors.Artist.AlreadyExists);
        }

        if (errors.Any())
        {
            return errors;
        }

        var artist = Artist.Create(name);

        await _artistRepository.AddAsync(artist, cancellationToken);

        return artist.Id;
    }
}