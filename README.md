# icyStdLib

*A lightweight standard library for C++ projects.*

|   Component    | Description |
|----------------|-------------|
| icyFileSystem  | cross-platform universal fullpath handler |
| icyString      | helper APIs for `std::string` ***(NOT A SPECIALIZED CLASS TYPE)*** |
| icyMswConsole  | console and printf for MSVC/Windows applications supporting pipe-redirection |
| icyLogger      | lightweight heap-free formatted text-log writer |

## icyFileSystem

*A Cross-Platform Universal Fullpath Handler for C++*

### How It Works

**Yes you can finally say goodbye to DOS-style filepaths...**

*`icyFileSystem`* works by emulating the universal filesystem path convention used by MSYS2 and Git For
Windows (via Git BASH). Drive letters are eliminated by way of using special reserved root
directory drive paths. Examples may speak louder than words:

```
c:\windows

vs. 

/c/windows
```

It's that simple.
*(well, not quite, but mostly yes it's that simple)*

#### Features of Universal Path Layout

 - simple parsing: forward-slash as only token delimiter
    - no more backslash-this and forward-slash-that. Ever.
 - easy to determine relative or absolute path
    - if first char is `/` then it's absolute, otherwise it's relative
 - standard and predictable path concatenation with absolute path override
 - plays nice with URI-style colon delimiter syntax used by some platforms
    - no risk of drive-letter-colon syntax conflicting with 
    - `git:` and `cdrom:` and `dev0:` and such

### Compatibility with Embedded File Systems

icyFileSystem can work with most embedded filesystem paths via hard-wiring path prefixes. Some examples:

```
umd:/path/to/file.txt
usb0:/path/to/file.txt

/cdrom/path/to/file.txt
/usb/path/to/file.txt
```

Many such embedded systems already use light-weight colon-free mount point prefixing (Sony Playstation systems
for example). `icyFileSystem` is a perfect compliment to working with those systems, normalizing everything into a
friendly, uniform path syntax for both device and host filesystem access.

## Caveats

#### DOS/Windows Non-portable Path behaviors are Not Supported

DOS-style paths have a number of special behaviors whch are not supported by most (or any?) other modern
operating systems. The following low-level "features" of DOS paths cannot be supported by `icyFilesystem`:

 - device-specific current working directory (cwd)
 - current working device/drive

By making no attempt to support these non-portable features, our filesystem is thus afforded the luxury of
greatly simplifying its API and implicit-conversion behavior as compared to the STL's `std::filesystem` API.

Additionally, the API of icyFileSystem is designed to allow for implicit conversion to the native host
filesystem API. 
