namespace TcpConfiguration;

public record TcpOptions
{
    public required string Host { get; init; }
    public required int Port { get; init; }
};