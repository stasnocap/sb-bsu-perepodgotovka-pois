using Mapster;
using Music.Application.Authentication.Commands.Register;
using Music.Application.Authentication.Common;
using Music.Application.Authentication.Queries.Login;
using Music.Contracts.Authentication;
using Music.Domain.User;

namespace Music.Api.Common.Mapping;

public class AuthenticationMappingConfiguration : IRegister
{
    public void Register(TypeAdapterConfig config)
    {
        config.NewConfig<RegisterRequest, RegisterCommand>();

        config.NewConfig<LoginRequest, LoginQuery>();
        
        config.NewConfig<AuthenticationResult, AuthenticationResponse>()
            .Map(dest => dest, src => src.User)
            .Map(dest => dest.Id, src => src.User.Id.Value)
            .Map(dest => dest.FirstName, src => src.User.FirstName.Value)
            .Map(dest => dest.LastName, src => src.User.LastName.Value)
            .Map(dest => dest.Email, src => src.User.Email.Value)
            ;
    }
}