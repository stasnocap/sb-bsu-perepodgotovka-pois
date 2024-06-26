﻿using MediatR;
using Music.Application.Authentication.Common;

namespace Music.Application.Authentication.Commands.Register;

public record RegisterCommand(string FirstName, string LastName, string Email, string Password)
    : IRequest<ErrorOr.ErrorOr<AuthenticationResult>>;