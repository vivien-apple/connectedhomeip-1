/**
 *
 *    Copyright (c) 2020 Project CHIP Authors
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#import "OnOffViewController.h"
#import "CHIPUIViewUtils.h"
#import "DefaultsUtils.h"
#import <CHIP/CHIP.h>

@interface OnOffViewController ()
@property (weak, nonatomic) IBOutlet UIButton * onButton;
@property (weak, nonatomic) IBOutlet UIButton * offButton;
@property (weak, nonatomic) IBOutlet UIButton * toggleButton;

@property (nonatomic, strong) UILabel * resultLabel;

@property (readwrite) CHIPDevice * chipDevice;

@end

@implementation OnOffViewController

// MARK: UIViewController methods

- (void)viewDidLoad
{
    [super viewDidLoad];
    [self setupUIElements];

    self.chipDevice = GetPairedDevice();
}

// MARK: UI Setup

- (void)setupUIElements
{
    self.view.backgroundColor = UIColor.whiteColor;

    // Title
    UILabel * titleLabel = [CHIPUIViewUtils addTitle:@"On Off Cluster" toView:self.view];

    // stack view
    UIStackView * stackView = [UIStackView new];
    stackView.axis = UILayoutConstraintAxisVertical;
    stackView.distribution = UIStackViewDistributionEqualSpacing;
    stackView.alignment = UIStackViewAlignmentLeading;
    stackView.spacing = 30;
    [self.view addSubview:stackView];

    stackView.translatesAutoresizingMaskIntoConstraints = false;
    [stackView.topAnchor constraintEqualToAnchor:titleLabel.bottomAnchor constant:30].active = YES;
    [stackView.leadingAnchor constraintEqualToAnchor:self.view.leadingAnchor constant:30].active = YES;
    [stackView.trailingAnchor constraintEqualToAnchor:self.view.trailingAnchor constant:-30].active = YES;

    // Create buttons
    [self addButtons:3 toStackView:stackView];

    // Result message
    _resultLabel = [UILabel new];
    _resultLabel.hidden = YES;
    _resultLabel.font = [UIFont systemFontOfSize:17];
    _resultLabel.textColor = UIColor.systemBlueColor;
    _resultLabel.lineBreakMode = NSLineBreakByWordWrapping;
    _resultLabel.numberOfLines = 0;
    [stackView addArrangedSubview:_resultLabel];

    _resultLabel.translatesAutoresizingMaskIntoConstraints = false;
    [_resultLabel.trailingAnchor constraintEqualToAnchor:stackView.trailingAnchor].active = YES;
    _resultLabel.adjustsFontSizeToFitWidth = YES;
}

- (void)addButtons:(NSInteger)numButtons toStackView:(UIStackView *)stackView
{
    for (int i = 1; i <= numButtons; i++) {
        // Create buttons
        UILabel * labelLight = [UILabel new];
        labelLight.text = [NSString stringWithFormat:@"Light %@: ", @(i)];
        UIButton * onButton = [UIButton new];
        onButton.tag = i;
        [onButton setTitle:@"On" forState:UIControlStateNormal];
        [onButton addTarget:self action:@selector(onButtonTapped:) forControlEvents:UIControlEventTouchUpInside];
        UIButton * offButton = [UIButton new];
        offButton.tag = i;
        [offButton setTitle:@"Off" forState:UIControlStateNormal];
        [offButton addTarget:self action:@selector(offButtonTapped:) forControlEvents:UIControlEventTouchUpInside];
        UIButton * toggleButton = [UIButton new];
        toggleButton.tag = i;
        [toggleButton setTitle:@"Toggle" forState:UIControlStateNormal];
        [toggleButton addTarget:self action:@selector(toggleButtonTapped:) forControlEvents:UIControlEventTouchUpInside];

        UIStackView * stackViewButtons = [CHIPUIViewUtils stackViewWithLabel:labelLight
                                                                     buttons:@[ onButton, offButton, toggleButton ]];
        stackViewButtons.axis = UILayoutConstraintAxisHorizontal;
        stackViewButtons.distribution = UIStackViewDistributionEqualSpacing;
        stackViewButtons.alignment = UIStackViewAlignmentLeading;
        stackViewButtons.spacing = 10;
        [stackView addArrangedSubview:stackViewButtons];
    }
}

- (void)updateResult:(NSString *)result
{
    _resultLabel.hidden = NO;
    _resultLabel.text = result;
}

// MARK: UIButton actions

- (IBAction)onButtonTapped:(id)sender
{
    UIButton * button = (UIButton *) sender;
    NSInteger endpoint = button.tag;
    [self updateResult:[NSString stringWithFormat:@"On command sent on endpoint %@", @(endpoint)]];
    
    CHIPOnOff * onOff = [[CHIPOnOff alloc] initWithDevice:self.chipDevice endpoint:endpoint queue:dispatch_get_main_queue()];
    [onOff on:^(NSError *error, NSDictionary *values) {
        NSString * resultString = (error != nil) ? [NSString stringWithFormat:@"An error occured: 0x%02lx", error.code] : @"On command success";
        [self updateResult:resultString];
    }];
}

- (IBAction)offButtonTapped:(id)sender
{
    UIButton * button = (UIButton *) sender;
    NSInteger endpoint = button.tag;
    [self updateResult:[NSString stringWithFormat:@"Off command sent on endpoint %@", @(endpoint)]];
    
    CHIPOnOff * onOff = [[CHIPOnOff alloc] initWithDevice:self.chipDevice endpoint:endpoint queue:dispatch_get_main_queue()];
    [onOff off:^(NSError *error, NSDictionary *values) {
        NSString * resultString = (error != nil) ? [NSString stringWithFormat:@"An error occured: 0x%02lx", error.code] : @"Off command success";
        [self updateResult:resultString];
    }];
}

- (IBAction)toggleButtonTapped:(id)sender
{
    UIButton * button = (UIButton *) sender;
    NSInteger endpoint = button.tag;
    [self updateResult:[NSString stringWithFormat:@"Toggle command sent on endpoint %@", @(endpoint)]];
    
    CHIPOnOff * onOff = [[CHIPOnOff alloc] initWithDevice:self.chipDevice endpoint:endpoint queue:dispatch_get_main_queue()];
    [onOff toggle:^(NSError *error, NSDictionary *values) {
        NSString * resultString = (error != nil) ? [NSString stringWithFormat:@"An error occured: 0x%02lx", error.code] : @"Toggle command success";
        [self updateResult:resultString];
    }];
}

@end
