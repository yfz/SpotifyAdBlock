# Spotify AdBlock Tool - Made By Const

A lightweight Windows utility that blocks Spotify advertisements by modifying the hosts file and managing the Spotify application process.

## Features

- 🔒 Blocks Spotify ad servers by modifying the system hosts file
- 🎵 Run once and enjoy ad-free Spotify forever!
- ⚡ Automatically terminates running Spotify processes
- 🚀 Launches Spotify with ad-free experience
- 🔧 Easy to use with automatic system
- 📦 Lightweight and portable

## How It Works

This tool works by adding known Spotify advertising domains to your system's hosts file and redirecting them to localhost (0.0.0.0), effectively preventing the application from connecting to ad servers. It also ensures a clean restart of Spotify to apply these changes immediately.

## Installation

### Option 1: Download Pre-built Release
1. Visit the [Releases page](https://github.com/yfz/SpotifyAdBlock/releases)
2. Download the latest `SpotifyAdBlock.exe` file
3. Run the executable

### Option 2: Build from Source
1. Clone the repository:
   ```bash
   git clone https://github.com/yfz/SpotifyAdBlock.git
   ```
2. Open the project in Visual Studio
3. Build the solution (Requires Windows SDK)

## Usage

1. Ensure Spotify is installed on your system
2. Run `SpotifyAdBlock.exe`
3. The tool will automatically:
   - Terminate any running Spotify processes
   - Update your hosts file to block ads
   - Launch Spotify ad-free
4. Press Enter to exit the tool

## Blocked Domains

The tool blocks the following advertising domains:
- `audio-ads.spotify.com`
- `pubads.g.doubleclick.net`
- `googleads.g.doubleclick.net`
- `spclient.wg.spotify.com`

## Requirements

- Windows 7 or newer
- Spotify installed in default location (%APPDATA%\Spotify\Spotify.exe)
- Administrator privileges (requested automatically)

## Notes

- This tool modifies system files (hosts file) which requires administrator privileges
- Some antivirus software might flag host file modifications as suspicious
- The tool is provided as-is without warranties
- Using ad blockers may violate Spotify's Terms of Service

## Troubleshooting

If you encounter issues:
1. Ensure you're running the latest version of Spotify
2. Check if your security software is blocking host file modifications

## Disclaimer

This tool is provided for educational purposes only. The developers are not responsible for any issues caused by using this software. Users assume all responsibility for any violations of Spotify's Terms of Service.

## Contact

For questions or support:
- Telegram: [@xconst](https://t.me/xconst)
- GitHub Issues: [Create an issue](https://github.com/yfz/SpotifyAdBlock/issues)
