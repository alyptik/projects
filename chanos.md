# ChanOS

A design for an operating system centered around filesystems of channels. It
probably needs a better name.

## Channels

Channels are (effectively) unidirectional streams, supporting either input or
output. Channels are connected by hooking up an output stream to an input
stream. All channels are forward seekable. Some channels may support seeking
backwards. Channels are named entities exposed through a filesystem. The unit
of streaming in a channel is a byte.

Channels may also be public or private in the sense that programs may set ACLs
as to what other programs (if any) may access a particular channel.

## Filesystem

Everything in ChanOS is a filesystem, and the only leaf nodes in the filesystem
are channels. This means that even "files" are actually filesystems. Data files
(like text) are provided synthetic filesystems by the kernel that expose input
and output channels for the files' content. Additionally, file metadata is
exposed through output channels. Some file properties (such as ACLs) have input
channels associated with them such that these can be modified.

Namespaces in ChanOS are per-process.

### ChanFS

A special namespace, /chan, exists per-process and defines the channels that
are currently available for the process to use. New channels are created by
making new files in this namespace.

### ProcFS

A special namespace, /proc, exists for all processes and is effectively a
global namespace. Through /proc, channels for other processes may be exported
discovered. Other information about processes is exported through this
interface as well, including debugging control interfaces.

New processes and threads are also created through this filesystem.

### GraftFS

Channels are connected via grafts. A graft is effectively a conduit that
connects an output channel to an input channel. Programs may be defined that
operate as grafts in the operating environment.

Grafts are exported through a namespace /graft and exist

Some special grafts exist:

 * `g`, which grafts a single output channel into a single input channel,
 * `mux`, which can multiplex several output channels into a single input
   channel, and
 * `tee`, which can duplicate a single output channel into multiple input
   channels.

Grafts can be used "anonymously" in such a way that they create the channels
that they connect.

### MapFS

A memory mapping filesystem is provided to allow programs to request memory
under the namespace /map.

### NetFS

Network protocols and services are created through the namespace /net.

## Processes and Threads

There is no distinction between threads and processes in the system. Threads
may spawn other threads. On thread creation, it can be specified whether the
new thread executes within the same address space. The terms "process" and
"thread" may be used interchangably.

## Syscalls

All OS functionality is exposed through operations on channels, which implement
the concept of a "file". As such, the only syscalls in the system have to do
with traditionally "file" operations:

 * `create`: Create a new channel.
 * `open`: Open an existing channel.
 * `read`: Read from a channel.
 * `write`: Write to a channel.
 * `seek`: Seek to a position in a stream.
 * `close`: Close a channel.

To ease working with hierarchical namespaces, the following syscalls exist:

 * `chdir`: Change the view of the current root namespace to the new namespace.
 * `bind`: Bind an existing namespace to a new or existing namespace.

