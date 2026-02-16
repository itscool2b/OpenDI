{ pkgs ? import <nixpkgs> {} }:
pkgs.mkShell {
  buildInputs = with pkgs; [
    plplot
    gcc
    ghostscript
  ];
  
  # Set compiler flags for PLplot
  shellHook = ''
    export CFLAGS=$(pkg-config --cflags plplot)
    export LIBS=$(pkg-config --libs plplot)
  '';
}
