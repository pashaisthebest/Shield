//
//  ViewController.m
//  Tester
//
//  Created by Andrey Ogrenich on 29/07/14.
//  Copyright (c) 2014 Andrey Ogrenich. All rights reserved.
//

#import "BTDevicesViewController.h"
#import "BTManager.h"
#import "DeviceCell.h"
#import "ShieldViewController.h"

@interface BTDevicesViewController () <UITableViewDataSource, UITableViewDelegate, BTManagerDelegate>

// IBOutlets
@property (weak, nonatomic) IBOutlet UITableView *tableView;
- (IBAction)searchTap:(id)sender;
@end

@implementation BTDevicesViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.title = @"Devices";
    [self addActivityIndicatorToNavigationBar];
}

- (void)viewWillAppear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:NO animated:animated];
    [[BTManager sharedInstance] setDelegate:self];
    [BTManager sharedInstance].discoveredShields = [NSMutableArray new];
    [[BTManager sharedInstance] scanForShieldsForSeconds:3.];
    [super viewWillAppear:animated];
}

- (void)viewWillDisappear:(BOOL)animated
{
    [self.navigationController setNavigationBarHidden:YES animated:animated];
    [super viewWillDisappear:animated];
}

//------------------------------------------------------------------------------------
#pragma mark - BTManagerDelegate

- (void)btManagerDidStartScanningForShields:(BTManager *)manager
{
    [self.activityIndicatorNavigation startAnimating];
}

- (void)btManagerDidEndScanningForShields:(BTManager *)manager
{
    [self.activityIndicatorNavigation stopAnimating];
}

- (void)btManagerUpdatedDiscoveredShields:(BTManager *)manager
{
    [self.tableView reloadData];
}

- (void)btManager:(BTManager *)manager errorOccured:(NSError *)error
{
    NSLog(@"WARNING: btManager:errorOccured:");
}

- (void)errorOccured:(NSError *)error
{
    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"BTLE"
                                                    message:[NSString stringWithFormat:@"Error %@ occured", @(error.code)]
                                                   delegate:nil
                                          cancelButtonTitle:@"OK"
                                          otherButtonTitles:nil];
    [alert show];
}

//------------------------------------------------------------------------------------
#pragma mark - UITableView methods

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return [[BTManager sharedInstance] discoveredShields].count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    Shield *device = [[[BTManager sharedInstance] discoveredShields] objectAtIndex:indexPath.row];
    DeviceCell *cell = [tableView dequeueReusableCellWithIdentifier:[DeviceCell cellIdentifier] forIndexPath:indexPath];
    [cell setDevice:device];
        
    return cell;
}

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    Shield *selectedShield = [[[BTManager sharedInstance] discoveredShields] objectAtIndex:indexPath.row];
    [[BTManager sharedInstance] connectToShield:selectedShield completionBlock:^(Shield *connectedShield) {
        [self performSegueWithIdentifier:SEGUE_ID_DEVICE_DETAIL sender:self];
    }];
    [self.tableView reloadData];
}

- (IBAction)searchTap:(id)sender
{
    [BTManager sharedInstance].discoveredShields = [NSMutableArray new];
    [self.tableView reloadData];
    [[BTManager sharedInstance] scanForShieldsForSeconds:3];
}

@end
