﻿using ErrorOr;
using MediatR;
using Music.Application.Common.Interfaces.Persistence;
using Music.Domain.Artists.Errors;
using Music.Domain.Artists.ValueObjects;

namespace Music.Application.Artists.Commands.ChangeArtistName;

public class ChangeArtistNameCommandHandler(IArtistRepository _artistRepository) : IRequestHandler<ChangeArtistNameCommand, ErrorOr<string>>
{
    public async Task<ErrorOr<string>> Handle(ChangeArtistNameCommand request, CancellationToken cancellationToken)
    {
        var errors = new List<Error>();

        var artistId = ArtistId.Create(request.Id);

        if (await _artistRepository.SingleOrDefaultAsync(artistId, cancellationToken) is not { } artist)
        {
            return Errors.Artist.NotFound;
        }
        
        var errorOrName = Name.Create(request.Name);
        errors.AddRange(errorOrName.ErrorsOrEmptyList);
        var name = errorOrName.Value;

        if (!errorOrName.IsError && artist.Name.Value != name.Value && await _artistRepository.AnyAsync(name, cancellationToken))
        {
            errors.Add(Errors.Artist.AlreadyExists);
        }
        
        if (errors.Any())
        {
            return errors;
        }
        
        artist.ChangeName(name);

        await _artistRepository.ChangeNameAsync(artist, cancellationToken);

        return request.Name;
    }
}