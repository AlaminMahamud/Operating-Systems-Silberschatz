# Operating System Concepts

[![Awesome](https://awesome.re/badge-flat2.svg)](https://awesome.re)

## Table Of Contents:

- [Basics](#basics)
- [Overview](#overview)
- [Process Management](#process-management)
- [Process Co-ordination](#process-co-ordination)
- [Memory Management](#memory-management)
- [Storage Management](#storage-management)
- [Protection and Security](#protection-and-security)
- [Distributed Systems](#distributed-systems)
- [Special Purpose Systems](#special-purpose-systems)
- [Case Studies](#case-studies)
- [Resources](#resources)


## basics

type of os:
- batch
- time sharing
- single user
- multi user
- distributed
- real time
- general purpose

interrupt

## Overview

- System Calls
- System Programs
- OS Design
  - policy vs mechanisms

critical modules that require high performance
- interrupt handler
- i/o manager
- memory manager
- cpu scheduler

two common models of ipc (inter process communication)
- message passing
- shared memory

virtual connections between processes, users, computer systems

**Background Services** are called services / subsystems / daemons 

Operating Systems Structure
- MS-DOS
![](./assets/MS-DOS%20Layer.png)
- Unix
![](./assets/Unix%20Layers.png)

Kernel Provides
- File System
- CPU Scheduling
- Memory Management

**Layered OS**
![](./assets/Layered%20OS.png)
- One Problem - Overhead system calls
- Another Problem - Designing Layers Order
- Fewer Layers with More Functionality

**MicroKernel** - All Non Essential Parts are moved to system programs and User Space
![](./assets/MicroKernel%20Typical%20Architecture.png)
Mac OSX Darwin is also partly based on the Mach MicroKernel

**Loadable Kernel Modules** - Linking service dynamically
![](./assets/Solaris%20Loadable%20Modules.png)

- Architecture of Mac OSX
![](./assets/Mac%20OSX%20Structure.png)
- Architecture of iOS
![](./assets/Architecture%20of%20iOS.png)
- Architecture of Android
![](./assets/Android%20OS%20Architecture.png)

OS Debugging

- Log File
- Core Dump
- Crash
- Crash Dump

What Kernel Do in unrecoverable situation?
Save Kernel's Memory state to a section of disk that does not have any `FileSystem`.  When Kernel encounter a unrecoverable error, it take it's entire content of memory or kernel owned part and dump it into disk section. when booting, a process runs and tries to gather the memory dump from the disk and save it as file in filesystem

Trace Listing

System Generation 

- CPU
- Boot Disk
- Memory
- Device
- OS Options

## Resources

- [What Happens when we boot a computer](https://www.geeksforgeeks.org/what-happens-when-we-turn-on-computer/)
- [Boot Block](https://www.geeksforgeeks.org/operating-system-boot-block/)


