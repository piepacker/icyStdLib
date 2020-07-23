# cppIcyStdLib

## IcyFileSystem

*A truly Cross-Platform Universal FileSystem API for C++*
***Say goodbye to DOS-style filepaths***

### How It Works

IcyGist FileSystem works by emulating the universal filesystem path convention used by MSYS2 and Git For
Windows (via Git BASH). On those syystems, drive letters are eliminated by way of using special reserved
root directory drive paths. That probably doesn't make a lot of sense. Examples should be simpler:

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

#### DOS/Windows Non-portable Path behaviors are Not Supported

DOS-style paths have a number of special behaviors whch are not supported by most (or any?) other modern
operating systems. The following low-level "features" of DOS paths cannot be supported by IcyGist Filesystem:

 - device-specific current working directory (cwd)
 - current working device/drive

By making no attempt to support these non-portable features, our filesystem is thus afforded the luxury of
greatly simplifying its API and implicit-conversion behavior as compared to the STL's `std::filesystem` API.

Additionally, the API of IcyGist FileSystem is designed to allow for implicit conversion to the native host
filesystem API. 
