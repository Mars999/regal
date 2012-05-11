//
//  main.m
//  minimal_ios
//
//  Created by Cass Everitt on 1/25/12.
//  Copyright 2012 n/a. All rights reserved.
//

#import <UIKit/UIKit.h>

int main(int argc, char *argv[])
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, nil);
    [pool release];
    return retVal;
}
