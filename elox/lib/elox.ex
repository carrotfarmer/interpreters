defmodule Elox do
  use Application
  alias Scanner

  def start(_type, _args) do
    args = System.argv()

    cond do
      length(args) > 1 ->
        IO.puts("Usage: elox [script]")
        System.halt(64)

      length(args) == 1 ->
        run_file(hd(args))

      true ->
        run_prompt()
    end

    {:ok, self()}
  end

  def run_file(file) do
    bytes = File.read!(file)
    run(String.trim_trailing(bytes))
  end

  def run_prompt do
    line = IO.gets("> ")

    if(line != :eof) do
      run(line)
      run_prompt()
    end
  end

  def run(source) do
    scanner = %{source: source}
    tokens = scanner |> Scanner.scanTokens()
    IO.inspect(tokens)
  end
end
