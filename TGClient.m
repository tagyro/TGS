//
//  TGClient.m
//  https://github.com/tagyro/TGS
//

#import "TGClient.h"

@implementation BasicEvent
@end

@implementation LoginEvent
@end

@implementation TGSession

+(JSONKeyMapper*)keyMapper
{
    return [[JSONKeyMapper alloc] initWithDictionary:@{@"sessionId":@"id"}];
}

@end

@implementation TGClient

static NSString *API_KEY = nil;
//
static NSString *API_ROOT_SERVER = @"https://api.tapglue.com/0.2/";
static NSString *API_DATE_FORMAT = @"2015-03-20T18:15:40.8+01:00";

+ (void)setAPIKey:(NSString *)apiKey {
    NSAssert(API_KEY == nil, @"API key should be set only once");
    API_KEY = apiKey;
}

static TGClient * _sharedClient = nil;

+ (instancetype)sharedClient {
    if (!_sharedClient) {
        NSAssert(API_KEY != nil, @"setAPIKey: should be called first");
        _sharedClient = [[TGClient alloc] init];
    }
    return _sharedClient;
}

- (instancetype)init {
    self = [super init];
    if (self) {
        NSAssert(API_KEY != nil, @"setAPIKey: should be called first");
//        __weak typeof(self) ws = self;
    }
    return self;
}

- (void)loginUser:(TGUser*)user {
    NSString *authStr = [NSString stringWithFormat:@"%@:%@", API_KEY, @""];
    NSData *authData = [authStr dataUsingEncoding:NSUTF8StringEncoding];
    NSString *base64authData = [authData base64EncodedStringWithOptions:0];
    NSString *authValue = [NSString stringWithFormat:@"Basic %@", base64authData];
    
    [[JSONHTTPClient requestHeaders] setValue:authValue forKey:@"authorization"];
    [[JSONHTTPClient requestHeaders] setValue:@"application/json" forKey:@"Content-Type"];
    [[JSONHTTPClient requestHeaders] setValue:@"application/json" forKey:@"accept"];
    //
    [JSONHTTPClient postJSONFromURLWithString:[API_ROOT_SERVER stringByAppendingString:[API_ROOT_SERVER stringByAppendingString:@"user/login"]]
                                       bodyData:[user toJSONData]
                                   completion:^(id json, JSONModelError *err) {
                                       if (err) {
                                           NSLog(@"error: %@",err);
                                       } else {
                                           NSLog(@"json: %@",json);
                                       }
                                   }];
}

- (void)createUser:(TGUser *)user {
    //
    NSString *authStr = [NSString stringWithFormat:@"%@:%@", API_KEY, @""];
    NSData *authData = [authStr dataUsingEncoding:NSUTF8StringEncoding];
    NSString *base64authData = [authData base64EncodedStringWithOptions:0];
    NSString *authValue = [NSString stringWithFormat:@"Basic %@", base64authData];
    
    [[JSONHTTPClient requestHeaders] setValue:authValue forKey:@"authorization"];
    [[JSONHTTPClient requestHeaders] setValue:@"application/json" forKey:@"Content-Type"];
    [[JSONHTTPClient requestHeaders] setValue:@"application/json" forKey:@"accept"];
    //
    
    [JSONHTTPClient postJSONFromURLWithString:[API_ROOT_SERVER stringByAppendingString:@"users"]
                                       bodyData:[user toJSONData]
                                   completion:^(id json, JSONModelError *err) {
                                       if (err) {
                                           LoginEvent *le = [LoginEvent new];
                                           le.error = err;
                                           PUBLISH(le);
                                       } else {
                                           self.me = [[TGUser alloc] initWithDictionary:json error:nil];
                                           //
                                           PUBLISH([LoginEvent new]);
                                       }
                                   }];
    
}

@end

@implementation TGUser

+(JSONKeyMapper*)keyMapper
{
    return [[JSONKeyMapper alloc] initWithDictionary:@{@"user_id":@"id"}];
}

@end

@implementation TGConnection

@end

@implementation TGDisplay
@end

@implementation TGObject

@end

@implementation TGEvent

@end