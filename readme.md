#  macOS IOSharedDataQueue regression workaround library

macOS 10.13.6 and 10.14 suffer from a serious regression causing stalls in IOSharedDataQueue, which is only fixed in 10.14.1.
To continue using the shared data queue in kexts and applications on 10.13.6, the application side needs to use the affected data queue client functions from macOS 10.13.5, which do not have this problem. 

This project bundles up the non-buggy versions of the functions

* `IODataQueueDequeue`
* `IODataQueuePeek`
* `IODataQueueEnqueue`
* `IODataQueueEnqueueWithReadCallback`

into a dylib which can be loaded on-demand by an application if running on an affected OS version. For example:

      typedef IOReturn (*IODataQueueDequeue_fn_ptr)(IODataQueueMemory* dataQueue, void* data, uint32_t* dataSize);
      IODataQueueDequeue_fn_ptr io_data_queue_dequeue_fn = IODataQueueDequeue; // from IOKit.framework
      
      if (running_affected_version())
      {
        void* data_queue_library = dlopen("libSharedDataQueue.dylib", RTLD_LAZY);
        if (data_queue_library != NULL)
        {
          void* sym = dlsym(data_queue_library, "IODataQueueDequeue");
          if (sym != NULL)
          {
            io_data_queue_dequeue_fn = (IODataQueueDequeue_fn_ptr)sym;
          }
        }
      }
      
      // Then use io_data_queue_dequeue_fn() in place of IODataQueueDequeue() in the app code.

## License

This is essentially all Apple's code, originally published at [opensource.apple.com](https://opensource.apple.com/source/IOKitUser/IOKitUser-1445.60.1/IODataQueueClient.c.auto.html) under the APSL. 
