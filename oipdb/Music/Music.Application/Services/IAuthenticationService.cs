namespace Music.Application.Services;

public interface IAuthenticationService
{
    ErrorOr.ErrorOr<AuthenticationResult> Register(string firstName, string lastName, string email, string password);
    ErrorOr.ErrorOr<AuthenticationResult> Login(string email, string password);
}