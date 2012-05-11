//
//  minimal_iosAppDelegate.h
//  minimal_ios
//
//  Created by Cass Everitt on 1/25/12.
//  Copyright 2012 n/a. All rights reserved.
//

#import <UIKit/UIKit.h>

@class minimal_iosViewController;

@interface minimal_iosAppDelegate : NSObject <UIApplicationDelegate>

@property (nonatomic, retain) IBOutlet UIWindow *window;

@property (nonatomic, retain) IBOutlet minimal_iosViewController *viewController;

@end
