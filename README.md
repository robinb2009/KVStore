# KVStore
Simple Key-Value Database.

Written in C++ 20, mostly relying on standard template library.

Some basic requirements:
- This DB is a standalone DB. Not sharded/distributed.
- There is no fault tolerance or protection for initial implementation. No journaling/WAL etc.
- Underlying DS yet to be decided. B+ trees or LSM trees.
- Only for small pieces of data, say < 1MB.

Future features:
- Make it distributed
- Add fault tolerance -- crashes should not cause inconsistencies
- Maybe add inherent snapshotting ability in the DB? -- Might need rewrite of underlying DS.