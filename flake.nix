{
  description = "MapLibre GL Native for Android CI Docker Container";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, nixpkgs, flake-utils }:
    {
      overlay = final: prev: {
        inherit (self.packages.${final.system});
      };
    }
    //
    flake-utils.lib.eachSystem [ "x86_64-linux" "aarch64-darwin" ] (system:
      let
        pkgs = import nixpkgs {
          inherit system;
          overlays = [
            self.overlay
          ];
        };
        paths = with pkgs; [
          cmake
          curl
          libuv
          libjpeg
          libpng
          icu60
          pkg-config
          xorg.libX11
          libGL
          glfw
          gcc10
          /* ninja */
          /* bash */
          /* nodejs */
          /* gnumake */
          /* coreutils */
          /* gnugrep */
          /* gnused */
          /* git */
          /* gradle */
          /* google-cloud-sdk */
          /* ccache */
          /*   pkgs.androidStudioPackages.stable; */
          /*   pkgs.androidStudioPackages.beta; */
          /*   pkgs.androidStudioPackages.preview; */
          /*   pkgs.androidStudioPackage.canary; */
        ];
      in
      {
        devShells = {
          default = pkgs.mkShell {
            packages = paths;
          };
        };
      }
    );
}


